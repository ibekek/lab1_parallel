{ pkgs }: {
	deps = [
		pkgs.mpi
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}