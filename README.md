# Simple Event Manager

## Design Goals

While there are quite a few event managers out there, it seemed that most of them were very opinionated about the

1. Message type
2. Thread model

This Event Manager was designed to not have an opinion about any of the two. Hence its simplicity.

This does mean that the user of this Event Manager needs to implement the thread model itself. Some might think that this makes this Event Manager **not** simple. Then again, when you want to mix and match different thread models, it's much simpler with this Event Manager.

## Building

Currently tested only with clang 17.0.6 but this is very straight forward C++17 code, so it should compile on any compiler.

```
cmake -S . -B build -GNinja
cmake --build build
```


If you don't have ninja dont add the *-GNinja* flag.

## Usage

Please look at the */tests* folder for usage examples.

## License

Currently distributed under MIT license.
This license was chosen because https://choosealicense.com/ recommended it as the most permisive license.
If there is a need for an aditional license, please contact me.
