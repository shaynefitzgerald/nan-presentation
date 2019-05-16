# Native Abstractions for Node.js Presentation

## Contributing

C/C++ Code is formatted using the `clang-format` extension for VSCode.
You can install it on OSX using `brew install clang-format` and use [this extension](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) to invoke it from VSCode.

If you have issues with errors reported by Intellisense for `<node_version.h>`, you will need to edit your `c_cpp_properties.json` to add your `node-gyp` headers to the `includePath`.

```json
"includePath": [
    "${workspaceFolder}/**",
    "~/.node-gyp/<node version>/include/node"
],
```

Where `<node version>` is the version of node you're compiling against.