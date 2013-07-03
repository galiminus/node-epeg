Install:

```
npm install epeg
```

Resize:

```
var epeg = require("epeg");

epeg.resize("./test.jpg", "./output.jpg", 100, 100);
```

Crop:

```
var epeg = require("epeg");

epeg.crop("./test.jpg", "./output.jpg", 200, 200, 100, 100);
```

Both can take an optional 'quality' parameter between 1 and 100 (default is 85):

```
var epeg = require("epeg");

epeg.resize("./test.jpg", "./nice.jpg", 100, 100, 90);
epeg.resize("./test.jpg", "./ugly.jpg", 100, 100, 10);
```
