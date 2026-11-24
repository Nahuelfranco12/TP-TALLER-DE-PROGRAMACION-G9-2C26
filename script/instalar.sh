#!/usr/bin/env bash
set -e

# informacion del proyecto y los puertos que se usan
NOMBRE="Stardew-Valley"
URL_REPO="https://github.com/Nahuelfranco12/TP-TALLER-DE-PROGRAMACION-G9-2C26.git"
CARPETA_REPO="TP-TALLER-DE-PROGRAMACION-G9-2C26"
CARPETA_BUILD="build-release"
HOST="localhost"
PUERTO=8080 # lo puedo cambiar si esta ocupado por otra cosa
ESPERA_SERVIDOR_SEGUNDOS=10 #lo que espero, si no atiende se cierra

# estos son los modulos y lo que se tiene que ejecutar
BIN_CLIENTE="taller_client"
BIN_SERVIDOR="taller_server"
BIN_EDITOR="taller_editor"
BIN_TESTS="taller_tests"

#aca es la direccion donde se instala
DIR_BIN="$HOME/.local/bin"
DIR_DATOS="$HOME/.local/share/$NOMBRE"
DIR_CONFIG="$HOME/.config/$NOMBRE"
DIR_INICIAL="$(pwd)"

LANZADOR_SERVIDOR="$NOMBRE-servidor"
LANZADOR_CLIENTE="$NOMBRE-cliente"
LANZADOR_EDITOR="$NOMBRE-editor"

# estas son las dependencias que instalo en el sistema
# son las de ubuntu (en teoria) no funcionaria en fedora o algo basado en arch
DEPENDENCIAS=(
  build-essential cmake git pkg-config iproute2 valgrind
  qt6-base-dev qt6-qpa-plugins libgl1-mesa-dev
  libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxss-dev
  libxkbcommon-dev libwayland-dev wayland-protocols libegl1-mesa-dev
  libasound2-dev libpulse-dev
  libopus-dev libopusfile-dev libxmp-dev libfluidsynth-dev fluidsynth
  libwavpack1 libwavpack-dev libfreetype-dev wavpack
)

PID_SERVIDOR=""
PREFIJO=()

informar() {
  printf '\n==> %s\n' "$1"
}

fallar() {
  printf '\nError: %s\n' "$1" >&2
  exit 1
}

mostrar_uso() {
  cat <<EOF
Uso: $0 [comando]

Sin comando: instala todo (dependencias, compilación, tests, archivos)
y lanza el servidor y el cliente.

Comandos:
  download: instala las dependencias con apt (pide sudo)
  build: compila
  tests: compila y corre los tests
  install: compila, corre los tests e instala
  run server|client|editor|jugar [--valgrind] corre lo instalado ("jugar" levanta el servidor y el cliente juntos)
EOF
}

es_raiz_del_repo() {
  [[ -f "$1/CMakeLists.txt" && -d "$1/client_src" && -d "$1/server_src" && -d "$1/common_src" ]]
}

ir_al_repo() {
  local dir_script
  dir_script="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  if es_raiz_del_repo "$dir_script"; then
    cd "$dir_script"
    return
  fi
  fallar "este comando se corre con el script dentro del repo."
}

ubicar_o_clonar_repo() {
  local dir_script
  dir_script="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  if es_raiz_del_repo "$dir_script"; then
    cd "$dir_script"
    return
  fi
  if ! es_raiz_del_repo "$CARPETA_REPO"; then
    informar "Clonando el repositorio"
    git clone "$URL_REPO" "$CARPETA_REPO"
  fi
  cd "$CARPETA_REPO"
}

instalar_dependencias() {
  if ! command -v apt-get >/dev/null; then
    fallar "este instalador es para Ubuntu/Xubuntu (necesita apt-get)."
  fi
  informar "Instalando dependencias (pide la contraseña de sudo)"
  sudo apt-get update
  sudo apt-get install -y "${DEPENDENCIAS[@]}"
}

build() {
  if [[ "${1-}" == "--clean" || "${1-}" == "-c" ]]; then
    informar "Borrando $CARPETA_BUILD/"
    rm -rf "$CARPETA_BUILD"
  fi
  informar "Compilando"
  cmake -S . -B "$CARPETA_BUILD" -DCMAKE_BUILD_TYPE=Release \
    -DTALLER_MAKE_WARNINGS_AS_ERRORS=OFF
  cmake --build "$CARPETA_BUILD" -j"$(nproc)"
}

correr_tests() {
  informar "Corriendo los tests"
  "./$CARPETA_BUILD/$BIN_TESTS"
}

copiar_archivos() {
  informar "Instalando en ~/.local y ~/.config"
  mkdir -p "$DIR_BIN" "$DIR_DATOS" "$DIR_CONFIG"

  install -m 755 "$CARPETA_BUILD/taller_client" "$DIR_BIN/$BIN_CLIENTE"
  install -m 755 "$CARPETA_BUILD/taller_server" "$DIR_BIN/$BIN_SERVIDOR"
  install -m 755 "$CARPETA_BUILD/editor/editor" "$DIR_BIN/$BIN_EDITOR"

  rm -rf "$DIR_DATOS/assets"
  cp -r assets "$DIR_DATOS/"
  if [[ -d maps ]]; then
    cp -r maps "$DIR_DATOS/"
  fi
}

avisar_path() {
  case ":$PATH:" in
  *":$DIR_BIN:"*) ;;
  *)
    informar "~/.local/bin no está en el PATH de esta terminal:"
    printf '    cerrá sesión y volvé a entrar para usar %s,\n' "$BIN_CLIENTE"
    printf '    %s y %s desde cualquier lado.\n' "$BIN_SERVIDOR" "$BIN_EDITOR"
    ;;
  esac
}

crear_lanzador() {
  local destino="$DIR_INICIAL/$1"
  cat >"$destino" <<EOF
#!/usr/bin/env bash
cd "$DIR_DATOS"
$2
EOF
  chmod +x "$destino"
}

crear_lanzadores() {
  informar "Creando los ejecutables en $DIR_INICIAL"
  crear_lanzador "$LANZADOR_SERVIDOR" \
    "exec \"$DIR_BIN/$BIN_SERVIDOR\" \"\${1:-$PUERTO}\""
  crear_lanzador "$LANZADOR_CLIENTE" \
    "exec \"$DIR_BIN/$BIN_CLIENTE\" \"\${1:-$HOST}\" \"\${2:-$PUERTO}\""
  crear_lanzador "$LANZADOR_EDITOR" "exec \"$DIR_BIN/$BIN_EDITOR\""
}

install_proyecto() {
  build "$@"
  correr_tests
  copiar_archivos
  crear_lanzadores
  avisar_path
}

verificar_instalado() {
  if [[ ! -x "$DIR_BIN/$1" ]]; then
    fallar "$1 no está instalado: corré primero '$0 install'."
  fi
}

esperar_servidor() {
  local intentos=$((ESPERA_SERVIDOR_SEGUNDOS * 4))
  for ((i = 0; i < intentos; i++)); do
    if ss -ltn "sport = :$PUERTO" | grep -q LISTEN; then
      return
    fi
    if ! kill -0 "$PID_SERVIDOR" 2>/dev/null; then
      fallar "el servidor se cerró al arrancar."
    fi
    sleep 0.25
  done
  fallar "el servidor no empezó a escuchar en el puerto $PUERTO."
}

cerrar_servidor() {
  if [[ -z "$PID_SERVIDOR" ]]; then
    return
  fi
  printf 'q\n' >&3 2>/dev/null || true
  for ((i = 0; i < 20; i++)); do
    if ! kill -0 "$PID_SERVIDOR" 2>/dev/null; then
      break
    fi
    sleep 0.25
  done
  kill "$PID_SERVIDOR" 2>/dev/null || true
  wait "$PID_SERVIDOR" 2>/dev/null || true
  PID_SERVIDOR=""
}

jugar() {
  verificar_instalado "$BIN_SERVIDOR"
  verificar_instalado "$BIN_CLIENTE"
  informar "Lanzando el servidor (puerto $PUERTO) y el cliente"

  local entrada
  entrada="$(mktemp -u)"
  mkfifo "$entrada"
  exec 3<>"$entrada"
  rm "$entrada"

  trap cerrar_servidor EXIT
  "$DIR_BIN/$BIN_SERVIDOR" "$PUERTO" <&3 &
  PID_SERVIDOR=$!
  esperar_servidor

  "${PREFIJO[@]}" "$DIR_BIN/$BIN_CLIENTE" "$HOST" "$PUERTO" || true
  cerrar_servidor
}

run() {
  local modo="${1-}"
  local opcion="${2-}"

  if [[ "$opcion" == "--valgrind" ]]; then
    PREFIJO=(valgrind --leak-check=full --show-leak-kinds=all)
  elif [[ -n "$opcion" ]]; then
    fallar "opción inválida '$opcion' (solo --valgrind)."
  fi

  cd "$DIR_DATOS" 2>/dev/null || fallar "no está instalado: corré primero '$0 install'."

  case "$modo" in
  server)
    verificar_instalado "$BIN_SERVIDOR"
    "${PREFIJO[@]}" "$DIR_BIN/$BIN_SERVIDOR" "$PUERTO"
    ;;
  client)
    verificar_instalado "$BIN_CLIENTE"
    "${PREFIJO[@]}" "$DIR_BIN/$BIN_CLIENTE" "$HOST" "$PUERTO"
    ;;
  editor)
    verificar_instalado "$BIN_EDITOR"
    "${PREFIJO[@]}" "$DIR_BIN/$BIN_EDITOR"
    ;;
  jugar)
    jugar
    ;;
  *)
    fallar "modo inválido '$modo' (server, client, editor o jugar)."
    ;;
  esac
}

if [[ $# -eq 0 ]]; then
  instalar_dependencias
  ubicar_o_clonar_repo
  install_proyecto
  run jugar
  exit 0
fi

COMANDO="$1"
shift

case "$COMANDO" in
download)
  instalar_dependencias
  ;;
build)
  ir_al_repo
  build "$@"
  ;;
tests)
  ir_al_repo
  build "$@"
  correr_tests
  ;;
install)
  ir_al_repo
  install_proyecto "$@"
  ;;
run)
  run "$@"
  ;;
-h | --help | help)
  mostrar_uso
  ;;
*)
  mostrar_uso
  fallar "comando inválido '$COMANDO'."
  ;;
esac
