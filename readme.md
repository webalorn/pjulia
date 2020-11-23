# Pjulia

Projet de compilation.

## Build

```bash
make fbison # Optinal, only if lexer.lpp or parser.ypp changed
make
```

## Usage

```bash
pjuliac path/to/file.jl

pjuliac [--parse-only] [--type-only] <path_to_julia_file>
```
