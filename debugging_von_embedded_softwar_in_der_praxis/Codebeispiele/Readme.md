# Clang-Tidy Setup

Dieses Projekt nutzt **Clang-Tidy**, um potenzielle Fehler und schlechte Praktiken im C++-Code aufzudecken.

## Installation

Unter Linux:

```bash
sudo apt install clang-tidy
```

1. Führe Clang-Tidy auf einer Quelldatei aus

```
clang-tidy ../main.cpp -- -I../
```
