# Kelvra ECS

`github.com/kelvralang/ecs` is an external native-performance entity-component-
system package for Kelvra. Its storage engine is implemented in C++; it is not
built into or linked by the Kelvra language runtime. Import it with
`const ecs = @import("github.com/kelvralang/ecs")` and create an initialized world with
`ecs.CreateWorld()`.

Components are deterministic fixed-size byte records. Prefer `CreateSchema()`
and `world.componentFromSchema(...)` to manual byte packing. Schemas support
all fixed-width integer and float types, booleans, and entity IDs with
little-endian encoding. They intentionally reject managed runtime values.

Queries match one to three component types. Their dense order is unstable, and
any structural world change invalidates active queries. Replacing existing
component bytes through `Query.set` is nonstructural and safe during iteration.
Call `Query.close()` and `World.close()` when practical; GC finalizers are a
safe fallback and are idempotent with explicit closure.

```kelvra
const ecs = @import("github.com/kelvralang/ecs")

var schema ecs.Schema = ecs.CreateSchema()
const x ecs.Field = schema.addF32("x")
const y ecs.Field = schema.addF32("y")

var bytes Array<u8> = schema.buffer()
schema.putF32(bytes, x, 10.0)
schema.putF32(bytes, y, 20.0)
```

See [examples/position_velocity.kel](examples/position_velocity.kel) for a
runnable Position/Velocity update loop using schemas, typed `f32` fields, and
queries. The low-level `component(name, size, alignment)` and raw-byte APIs are
for interoperability and advanced packed-data use cases.

The repository contains the public source wrapper at its root and the private
`github:ecs-native` binding under `native/`. See `lib/README.md` for the
complete layout, lifetime, and C API rules.

Build the C++ package and its tests independently from Kelvra:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```
