# Resistor "Combinator"

Resistor "Combinator", supports both series and parallel--only accepts 2 Resistors.

All information about the apps can be found in `--help` options after build or run

## Quick Start (No Setup Required)

If you have Nix active with flakes enabled, you can interact with the app immediately from the root directory.

### Run Directly
```bash
nix run
```

### Build Locally
```bash
nix build
./result/bin/rescomb
```

### Develop Code
```bash
nix develop
# inside the shell:
gcc main.c -o local-build
```

## Alternate installation

There is `default.nix` you can use if want to add it in your NixOS systems as local packages, or use flake inputs. Depends on what you need the most.

Or if you non-Nix users, make sure `gcc` installed on your systems.
