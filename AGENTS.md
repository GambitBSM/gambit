# GAMBIT – agents guidelines

GAMBIT (*Global And Modular BSM Inference Tool*) is a modular C++/Fortran/Python framework for global fits of BSM physics models. It is built and run on Linux and macOS, with GCC, Clang and Intel toolchains, from laptops to MPI clusters. Prefer standard, portable fixes over ones tied to the local machine's setup.

## Building

- Builds are slow and memory-hungry, even partial ones, so treat every build as costly. Build incrementally in the existing `build*/` directory with its current CMake options, and keep it intact: run `clean` targets only when absolutely necessary.
- Re-run `cmake` after adding/removing source files or editing rollcall, model or backend macros; harvester scripts regenerate code from them.

## Code

- `ExampleBit_A/` is the reference module.
- Backend source is downloaded at build time; backend changes go in `Backends/patches/<backend>/`.
- Write for the typical reader: a physics PhD student who knows C++ but is not a C++ specialist. Prefer explicit code over compact or clever code, even when it is longer.
- Keep comments brief, timeless and in the style of the surrounding file: describe the code as it is, not how it got there.
- Never add an agent's name to author fields.
- Format only the lines you change (`.clang-format`).

## Git

- Commit source only; keep build and run outputs out of history.
- Open pull requests only when a human explicitly asks.
- `git push` only to `agents/*` branches.

