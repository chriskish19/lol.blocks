# check if a scoop package is installed or not
function is_spkg_installed{
    param(
        [string]$pkg_name
    )

    return Get-Command $pkg_name -ErrorAction SilentlyContinue
}



# Ensure script stops on error
$ErrorActionPreference = "Stop"

# Check if scoop is installed
if (-not (Get-Command scoop -ErrorAction SilentlyContinue)) {
    Write-Host "Scoop not found. Installing Scoop..."
    Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
    Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression
}

# Desired packages (can include "main/" or other bucket prefixes)
$packages = @(
    "cmake",
    "ninja",
    "git",
    "vcpkg"
)


foreach ($pkg in $packages) {
    if (-not (is_spkg_installed($pkg))) {
        Write-Host "Installing $pkg..." -ForegroundColor Yellow
        $full_pkg_name = "main/" + $pkg
        scoop install $full_pkg_name
    } else {
        Write-Host "$pkg is already installed." -ForegroundColor Green
    }
}

# gnu tool chain
scoop bucket add versions
scoop install versions/mingw-winlibs-llvm-ucrt

