# Stapel
Stapel is a tiny, visual (soon!) stack machine and language.

To build, test, and clean:

```sh
just build  # Build.
just test   # Run the tests.
just clean  # Remove build artifacts.
```

Usage:

```sh
stapel PROGRAM
```

Check out the language [reference](reference.md) and [example programs](examples/).


## Limitations and Bugs
This is very much a WIP project, so beware!
    - I haven't gotten around to resizable arrays yet, so very
      long programs or labels will crash it!
    - The code needs some refactoring and cleanup.
    - There's probably bugs!
    - Error messages for invalid programs is quite obtuse.

