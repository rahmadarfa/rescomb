{ pkgs, ... }:
pkgs.stdenv.mkDerivation {
  pname = "rescomb";
  version = "1.0";
  src = ./.;

  nativeBuildInputs = [ pkgs.gcc ];

  buildPhase = ''
    gcc -o rescomb main.c
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp rescomb $out/bin
  '';
}
