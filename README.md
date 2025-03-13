# Vizo, a C package manager 


## Example

**mybuild.py**:
```python
import vizo

project = vizo.Project() 
dev = project.new_profile("dev")
dev.add_c_args("-g", "-O0")
release = project.new_profile("release")
release.add_c_args("-O3")

exe = project.new_exe_target(profiles=[dev, release])


exe.add_files("src/*")
exe.include_dir("include")
```
**vizo.json**:
```json
{
	"name": "helloworld",
	"build": "mybuild.py",
	"default-profile": "dev"
	"deps": {
		"llvm": "url+",
		"yacc": "12.0"
	}
}
```
**Usage**:
```
vizo build // will build with the profile dev (default profile)
vizo build --profile release 
```

**Note**: running your build script with python will not work. Vizo will setup and call for you 

**Notes**:
  Your project variable must be named as project if you want to name it differently use `vizo.use_custom_project_name("<your name>")`
  for example: 
  ```python
  import vizo
  vizo.use_custom_project_name("myproject")
  myproject = vizo.Project()
  // ...
  ```


