Install:

```
npm install epeg
```

Resize:

```
var epeg = require("epeg");

image = new epeg.Image({path: "./test.jpg"}))
image.resize(100, 100).saveTo("./output.jpg");
```

Crop:

```
var epeg = require("epeg");

image = new epeg.Image({path: "./test.jpg"}))
image.crop(200, 200, 100, 100).saveTo("./output.jpg");
```

Both can take an optional 'quality' parameter between 1 and 100 (default is 85):

```
var epeg = require("epeg");

image = new epeg.Image({path: "./test.jpg"}))
image.resize(100, 100, 50).saveTo("./ugly.jpg");
```
