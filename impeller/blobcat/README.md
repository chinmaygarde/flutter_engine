# Blobcat

Impeller deals with shaders in the form of libraries. Some backends like Metal
already have a notion of shader library (``.metallib` files and the like).
Others deal with shaders discretely (OpenGL via GLSL and Vulkan via SPIR-V).
Blobcat packages shaders of backends that don't have concept of a library into a
single library with a known format.
