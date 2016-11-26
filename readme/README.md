https://gist.github.com/dergachev/4627207

http://superuser.com/questions/414553/is-there-a-command-analogous-to-afinfo-for-videos-on-a-mac-os-x

```
ffmpeg -i binary2d.mov -s 680x720 -pix_fmt rgb24 -f gif - | gifsicle --optimize=3 --delay=3 > binary2d.gif
```

mediainfo binary2d.mov  | grep -i "width"
mediainfo binary2d.mov  | grep -i "height"


rm binary2d.gif && ffmpeg -i binary2d.mov -s 325x360 -pix_fmt rgb24 binary2d.gif
ffmpeg -i binary3d.mov -s 342x360 -pix_fmt rgb24 binary3d.mov

ffmpeg -i binary2d.mov -s 342x360 -pix_fmt rgb24 -f gif - | gifsicle --optimize=3 --delay=3 > binary2d.gif
ffmpeg -i binary3d.mov -s 342x360 -pix_fmt rgb24 -f gif - | gifsicle --optimize=3 --delay=3 > binary3d.gif

