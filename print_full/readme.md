## write to unwriteable stdout

Rust stdlib is checking stream handler and panic if it is not writeable - 
[source](https://github.com/rust-lang/rust/blob/80c091958f05e573433df974f8d2f2bc3a3eadfb/library/std/src/io/stdio.rs#L1122).

C++ stdlib does not, sou your cout/println will succeed even if there is no space left.

```bash
$ gcc main.c -o clang
$ g++ main.cpp -o cpp
$ rustc main.rs -o rust

$ ./clang
Hello CLang
$ ./cpp
Hello CPP
$ ./rust
Hello Rust

# No errors from printf:
$ ./clang > /dev/full
$
# No errors from cout:
$ ./cpp > /dev/full
$
# Only Rust stdlib will produce an error in that scenario:
$ ./rust > /dev/full
thread 'main' panicked at library/std/src/io/stdio.rs:1118:9:
failed printing to stdout: No space left on device (os error 28)
note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace
$
```

Note: when file exists but is not writeable, error will be produced by the shell:

```bash
$ touch stdout && chmod -w stdout
$ ./clang > stdout
-bash: stdout: Permission denied
$ ./rust > stdout
-bash: stdout: Permission denied
```
