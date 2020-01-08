# union_of

Allows declaration of union type using a template. All types in the union must be [POD types](https://en.cppreference.com/w/cpp/named_req/PODType) and have the same size in bytes. This is intended to be used when working with data formats where exact type may not be obvious when reading data.

## Example

See `example.cpp` for usage info.

```cpp
// Initialize with all zeros
union_of<int, float, unsigned> data{};
// Initialize from existing value
union_of<int, float, unsigned> data{1234};
// Initialize from binary data pointer
union_of<int, float, unsigned> data{ptr, union_set_data_tag{}};
```
