# Stapel
Stapel is a tiny, visual stack machine and language.

To build, test, and clean:

```sh
just build  # Build.
just test   # Run the tests.
just clean  # Remove build artifacts.
```

Usage:

```sh
stapel PROGRAM [--plain]
```

Check out the language [reference](reference.md) and [example programs](examples/).
You can find even more example programs in the [test](test/) directory.


## What You'll Need
A C compiler and (optionally) [just](https://just.systems/) if you want
to use the pre-made recipes. You'll also need the
`ncurses` development libraries.


## Limitations and Bugs
This is very much a WIP project, so beware!

* I haven't gotten around to resizable arrays yet, so very
  long programs or labels will crash it!
* The code needs some refactoring and cleanup.
* There's probably bugs!
* Error messages for invalid programs is quite obtuse.
* The `SCAN` instruction doesn't play nice with the visual stack machine.

---

**Note: Generative AI was NOT involved in any part of this project.**
