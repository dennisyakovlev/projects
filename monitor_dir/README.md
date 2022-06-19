# Watch Directory
Watch a directory for certain changes using `inotifywait`.

## Origin
Originally came into existence because needed to terminate large program, without debugger, at specific section after a file was created in folder.

## Notes
Don't use `popen`, since creates extra processes you cant control. `fork` twice  
&nbsp;1) `exec` first child process with `inotifywait`  
&nbsp;2) monitor out of `inotifywait` in second child process  
This way, all children always terminate, even without `kill(0, SIGKILL)` being delived.