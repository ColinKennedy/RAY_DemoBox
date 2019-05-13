## Installation Steps

### Build

```bash
mkdir build
cd build
cmake ..
make
```


### Make Interface
Unlike traditional Houdini plugins (COPs, SOPs, w/e)

creating a Mantra procedural plugin does not actually define an
interface. So running `make` isn't going to actually create a Houdini
node that will be visible in a network context (e.g. You can't just
press [Tab] in a SHOP and expect it to show up.). You must make a new
SHOP operator type to actually get it to work.

1. Go to Windows > Asset Manager
2. Copy a Procedural SHOP (any is fine. I did the Program Procedural)
3. Make a new operator from it and save the operator
4. Change the parameters of the operator to be whatever you need it to be. In this procedural's case, it takes no parameters
5. Drop down your operator type in a SHOP Network, Click the operator's edit cog button and go to "Type Properties"
6. Go to the Node tab and change "Shader Name" to the className of your procedural (in this case "demobox")
7. Save the new operator and its settings


### Applying The Procedural
- Create a SHOP Network
- Dive into it and create your new operator
- Create a Geometry Object SOP
- In the Geometry node's "Render" tab, go to the "Geometry" sub-tab and
set its "Procedural Shader" to the absolute path to the operator that
you made earlier

And that's it, you're done. Render and your procedural should show up


## References
Most helpful - https://forums.odforce.net/topic/6106-vrayprocedural-in-h9/
Note: The VRAYProcedural file that most people talk about is actually deprecated. Don't use guides that use it! - https://www.sidefx.com/docs/hdk/_h_d_k__r_a_y__procedural.html#HDK_RAY_Procedural_Install
Example of guides to avoid 
 - https://forums.odforce.net/topic/11927-vray-procedurals-in-windows
 - https://forums.odforce.net/topic/17137-vray-procedural-on-mac
