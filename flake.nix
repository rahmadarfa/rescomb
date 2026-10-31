{
  description = "So called Resistor \"Combinator\"";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        # Allows you to run: nix build
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "rescomb";
          version = "0.1.0";
          src = ./.;
          buildInputs = [ pkgs.gcc ];
          buildPhase = ''
            gcc main.c -o rescomb
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp rescomb $out/bin/
          '';
        };

        # Allows you to run: nix run
        apps.default = {
          type = "app";
          program = "${self.packages.${system}.default}/bin/rescomb";
        };

        # Allows you to run: nix develop
        devShells.default = pkgs.mkShell {
          buildInputs = [ pkgs.gcc ];
        };
      }
    );
}

