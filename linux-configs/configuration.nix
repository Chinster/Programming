{ config, pkgs, ... }:

{
  imports =
    [
      ./hardware-configuration.nix
    ];

  # Use the systemd-boot EFI boot loader.
  boot.loader.systemd-boot.enable = true;
  boot.loader.efi.canTouchEfiVariables = true;

  networking.hostName = "analyze";
  networking.networkmanager.enable = true;


  time.timeZone = "America/New_York";

  nixpkgs.config.allowUnfree = true;

  environment.systemPackages =
  let
    base = with pkgs; [
      blender firefox steam
      wine transmission_gtk p7zip
      vim git python3 gcc file
      redshift rxvt_unicode i3status
    ];
    python_packages = with pkgs.python35Packages; [
      numpy
    ];
    rust_packages = with (import <unstable> {}); [
      rustc cargo
    ];
  in
    base ++ python_packages ++ rust_packages;

  #if config.services.xserver.enable then

  services.xserver = {
    enable = true;
    windowManager.i3.enable = true;
    displayManager.lightdm.enable = true;
    libinput.enable = true;
    xkbOptions = "ctrl:nocaps";
  };
  hardware.opengl.driSupport32Bit = true;

  users.extraUsers.yutoo = {
    isNormalUser = true;
    extraGroups = [ "wheel" "networkmanager" ];
    uid = 1000;
  };


  # The NixOS release to be compatible with for stateful data such as databases.
  system.stateVersion = "17.03";

  nix.gc.automatic = true;
  nix.gc.dates = "00:00";
}
