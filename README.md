## Playground for Morfeusz


Compling for development:
```bash
g++ main.cpp -o main -L lib -I include -l morfeusz2 -Wl,-rpath,\$ORIGIN/lib && ./main
```