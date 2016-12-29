https://gist.github.com/dergachev/4627207

http://superuser.com/questions/414553/is-there-a-command-analogous-to-afinfo-for-videos-on-a-mac-os-x

```
ffmpeg -i binary2d.mov -s 680x720 -pix_fmt rgb24 -f gif - | gifsicle --optimize=3 --delay=3 > binary2d.gif
```

mediainfo binary2d.mov  | grep -i "width"
mediainfo binary2d.mov  | grep -i "height"


ffmpeg -i binary2d.mov -s 290x310 -pix_fmt rgb24 binary2d.gif #todo figure out why this looks shit
ffmpeg -i binary3d.mov -s 290x310 -pix_fmt rgb24 binary3d.mov

//ffmpeg -i binary2d.mov -s 342x360 -pix_fmt rgb24 -f gif - | gifsicle --optimize=3 --delay=3 > binary2d.gif
//ffmpeg -i binary3d.mov -s 342x360 -pix_fmt rgb24 -f gif - | gifsicle --optimize=3 --delay=3 > binary3d.gif



steps
1. record 2d
2. solve 2d
3. save log file
4. screenshot 2d solved
5. downsize 2d solved by 50%
6. open 3d
7. solve 3d
8. save log file
9. record 3d enough to loop
10. trim 3d
11. save 3d
12. process .mov -> .gif
