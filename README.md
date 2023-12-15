# Hykeys

When enabled all keypresses will be sent to the Hyprland IPC socket file.

This will allow for per keyboard bindings

# Building

Should work on versions above v0.33.0

```bash
hyprpm add https://github.com/Euro20179/HyKeys
```

## Output format

keyboard-name,modmask,state,key,keycode

Descriptions:
- keyboard-name: name of the keyboard that pressed/released the key
- modmask (bitfield): the current modifier keys being pressed
    - shift: 1
    - capslock: 2
    - ctrl: 4
    - alt: 8
    - windows: 64
- state: either down (when key is pressed) or up (when key is released)
- key: always empty
- keycode: the keycode that is sent
