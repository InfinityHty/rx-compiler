# Build the C++ compiler once before testing: CMake configure + incremental
# build into target/build (first full build takes a few minutes).
BUILD = cmake -S . -B target/build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build target/build -j

# Semantic check: exit 0 to accept {source}, 1 to reject it.
SEMANTIC = ./target/build/rx {source}

# Codegen (尚未实现): compile {source} into RV32IM assembly at {output}.
# 等你的编译器支持 --codegen 和 -o 参数后取消注释。
# CODEGEN = ./target/build/rx --codegen {source} -o {output}

# Run RV32IM assembly in REIMU.
RUN = xmake run -P vendor/REIMU reimu --memory=256M --stack=1M \
    -f {output} -o {stdout} -p {profile} 1>&2
