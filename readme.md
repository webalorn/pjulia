# Pjulia

Projet de compilation.

## Build

```bash
make fbison # Optinal, only if lexer.lpp or parser.ypp changed
make pjulia
```

## Usage

```bash
pjulia path/to/file.jl

pjulia [--parse-only] [--type-only] <path_to_julia_file>
```
