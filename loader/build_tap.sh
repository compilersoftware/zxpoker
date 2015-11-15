#!/bin/sh
#
# * Como realizar la pantalla:
# 
# - loader.tap : obtenido a partir de loader.bas.
#   Es un cargador (loader.bas) que hace lo siguiente:
#    - Borrar la pantalla.
#    - Cargar la pantalla en memoria.
#    - POKEar unos valores para no aparezca "BYTES: juego".
#    - Cargar el bloque de codigo y saltar a el.
#
# - zxpoker-loadscr.tap: pantalla de presentacion del juego
#   en formato tap. Para obtenerla, coger el scr y sacar un
#   tap con scr2tap. Ir al emulador y hacer:
#
#     MERGE ""
#     LOAD "" CODE 32768,6912
#     (ahora en el emulador fuse Tape -> Clear Tap)
#     SAVE ""
#     (ahora en el emulador fuse Tape -> Write -> zxpoker-loadscr.tap)
#     (tambien se puede extraer el bloque con un editor de taps como un tap).
#
# - zxpoker-cm.tap: tap con el bloque de codigo maquina del programa. Hay
#   que ver el tama�o del bloque y su inicio de ejecucion (en el browser
#   de cintas y en el listado BASIC) y hacer (por ej):
#
#     MERGE ""
#     LOAD "" CODE 32768,tamanyo
#     (ahora en el emulador fuse Tape -> Clear Tap)
#     SAVE "zxpoke.bin" CODE 32768,tamanyo
#     (ahora en el emulador fuse Tape -> Write -> zxpoker-cm.tap)
#
# * Programas necesarios: BAS2TAP, SCR2TAP, cat.
#
#
# Tras todo eso, se ejecuta el siguiente script:
#

bas2tap -a10 -szxpoker loader.bas
cat loader.tap zxpoker-loadscr.tap zxpoker-cm.tap > ../zxpoker-with-loading-screen.tap


