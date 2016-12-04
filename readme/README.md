https://gist.github.com/dergachev/4627207

```
ffmpeg -i binary2d.mov -s 680x720 -pix_fmt rgb24 -f gif - | gifsicle --optimize=3 --delay=3 > binary2d.gif
```