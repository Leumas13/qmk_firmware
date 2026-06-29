# satomoga Corne keymap

Base skeleton for a QWERTY Corne using an OS-level English International layout.
Accents and special Spanish characters should come from the operating system with
Right Alt / AltGr instead of reactive firmware accents.

## Layer map

- `_BASE`: QWERTY typing, Right Alt available for EN International / AltGr.
- `_NUM` / layer 1: numpad-style number layer on the right half.
- `_SYM` / layer 2: symbols and brackets using normal US/EN-International positions.
- `_CFG` / layer 3: RGB controls, media, brightness, and bootloader.
- `_NAV` / layer 4: navigation, arrows, page movement, and common edit shortcuts.
- `_MOUSE` / layer 5: mouse movement, wheel, and buttons.
- `_FUN` / layer 6: function keys and safe bracket macros.
- `_EXTRA` / layer 7: empty expansion layer.

## RGB

RGB is split by LED type:

- `rgb_underglow.c`: bottom/reverse PCB underglow. It paints every
  `LED_FLAG_UNDERGLOW` LED with the selected OS color.
- `rgb_handlers.c`: per-key RGB layer patterns. It mirrors the keymap with
  `LAYOUT_split_3x6_3`, so each color entry is in the same physical position as
  the keycode in `keymap.c`.

The underglow color follows the selected OS:

- Windows: green
- macOS: blue
- Linux: white

Use `OS_SWITCH` to rotate between modes or `OS_WIN_MODE`, `OS_MAC_MODE`, and
`OS_LINUX_MODE` to select one directly.

## OS-specific actions

OS mode also drives semantic shortcut keycodes in `os_handlers.c`. Use these in
`keymap.c` instead of hardcoded `C(...)` shortcuts when a key should behave
differently per operating system:

- `OS_UNDO`, `OS_REDO`, `OS_CUT`, `OS_COPY`, `OS_PASTE`
- `OS_WORD_LEFT`, `OS_WORD_RIGHT`
- `OS_HOME`, `OS_END`

To add another OS-aware action:

1. Add a custom keycode in `shared.h` between `OS_END` and `M_PAREN`.
2. Add the Windows, macOS, and Linux outputs to `os_keycode_maps` in
   `os_handlers.c`.
3. Use the new keycode in `keymap.c`.

When macOS mode is active, QMK swaps Ctrl and GUI on both sides so physical Ctrl
positions behave as Command. Windows and Linux modes keep the normal Ctrl/GUI
mapping.

## Imported from Vial

`keymap.vil` was used as the source for the base layout and layer numbers. Text
macros from Vial were intentionally not imported into firmware source.
