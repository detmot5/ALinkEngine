import subprocess, os, shutil, sys
build_dir = "build"
windows_binary_dir = "build\\Windows"
linux_binary_dir =  "build/Linux"


platform_windows = "windows"
platform_linux = "linux"

linux_name = "ubuntu2004"

def build_linux():
  return subprocess.run([f"{linux_name}", f"run", 
                         f"cd {linux_binary_dir} && ", 
                         "cmake ../../src &&",
                         "make"
                         ], 
                         shell=True)


def build_windows():  
  print("wind")
  return subprocess.run([ "cmd &&", f"cd {windows_binary_dir}",
                          "make"
                        ], shell=True)




def clean_platform(platform_dir):
  print(f"Processing clean for {platform_dir}")
  if len(os.listdir(platform_dir)) != 0:
    shutil.rmtree(platform_dir)
  if "Linux" not in os.listdir(build_dir):
    os.mkdir(platform_dir)
  else: print(f"Nothing to clean in {platform_dir}")


def parse_process_status(platformName, statuscode):
  if statuscode == 0: print(f"Build for {platformName} successfully completed with exit code: {statuscode}")
  else: print(f"Build for {platformName} failed with exit code: {statuscode}")
  return statuscode

def check_build_dir():
  if build_dir not in os.listdir("./"):
    os.mkdir(f"./{build_dir}")
  if os.path.basename(windows_binary_dir) not in os.listdir(build_dir):
    os.mkdir(windows_binary_dir)
  if os.path.basename(linux_binary_dir) not in os.listdir(build_dir):
    os.mkdir(linux_binary_dir)





def run_build(platform, run_clean):
  check_build_dir()
  if platform == platform_linux:
    print(f"Building For Linux using WSL {linux_name}")
    if(run_clean): clean_platform(linux_binary_dir)
    parse_process_status(linux_name, build_linux().returncode)
  elif platform == platform_windows: 
    print("Building for Windows")
    if(run_clean): clean_platform(windows_binary_dir)
    parse_process_status("Windows", build_windows().returncode)
  elif platform == "all":
    print("Buildin All")
    if(run_clean):
      clean_platform(linux_binary_dir)
      clean_platform(windows_binary_dir)
    print(f"Building For Linux using {linux_name}")
    linux_status = parse_process_status(linux_name, build_linux().returncode)
    print("Building for Windows")
    windows_status = parse_process_status("Windows", build_windows().returncode)
    print("Build results")
    if linux_status == 0: print(f"Wsl {linux_name}: SUCCESS")
    else: print(f"WSL {linux_name}: FAIL")
    if windows_status == 0: print("Windows: SUCCESS")
    else: print("Windows: FAIL")


def main():
  if(len(sys.argv) > 2):
    run_build(sys.argv[1] if sys.argv[1] == "linux" or "windows" else "all", 
              True if sys.argv[2] == "clean" else False)
  elif(len(sys.argv) > 1):
    run_build(sys.argv[1], False)
  else:
    run_build("all", False)



if __name__ == "__main__": main()


