# Tiled type properties

In Tiled, you can set a type and properties to objects in object layers. Case matters for porperty names and values defined in this document. Default values written here are used if the property is not explicitly defined.

## Map properties

RedBox has some properties that will be read and interpreted when loading a tile map.

<table>
<tr>
<th>Name</th>
<th>Description</th>
<th>Default value</th>
</tr>
<tr>
<td>zInterval</td>
<td>Z interval between each layer. When layers are added to the state after being loaded. This will be the distance in Z between each layer for the render order. This will let you add bodies to the state between layers. If the Z interval is set to 0, the layers will still be rendered in the right order, but you will not be able to add bodies between the layers. If the value is negative, the order of the layers will actually be rendered in the reverse order.</td>
<td>100</td>
</tr>
<tr>
<td>zStart</td>
<td>Z of the first layer. The second layer would have a z of zStart + zInterval.</td>
<td>0</td>
</tr>
</table>

## Layer properties

Only one property is read and interpreted by RedBox when reading a tile map.

<table>
<tr>
<th>Name</th>
<th>Description</th>
<th>Default value</th>
</tr>
<tr>
<td>z</td>
<td>Z coordinate of the layer. Overrides the Z calculated by the zStart and zInterval specified in the tile map's properties. Optional.</td>
<td></td>
</tr>
</table>

## Object types available

RedBox has some pre-defined types you can set that RedBox will read and initialize. To load the types in Tiled, open the "Preferences" window and select the "Object Types" tab. Then, you can either enter the types manually or import them from the "redbox_types.xml" file available with this documentation.

* RedBox::Sprite
* RedBox::InanimateSprite

### Common properties

Here's the list of properties that RedBox will read for both "RedBox::Sprite" and "RedBox::InanimateSprite". Boolean values are represented with "0" for false and "1" for true.

If a given value is invalid (for example, if you put "bob" as the value for "velocity.x"), the default value will be used when loading the body.

<table>
<tr>
<th>Name</th>
<th>Description</th>
<th>Default value</th>
</tr>
<tr>
<td>velocity.x</td>
<td>Horizontal velocity of the object (float or integer value).</td>
<td>0</td>
</tr>
<tr>
<td>velocity.y</td>
<td>Vertical velocity of the object (float or integer value).</td>
<td>0</td>
</tr>
<tr>
<td>maximumVelocity.x</td>
<td>Maximum horizontal velocity of the object (float or integer value). Negative value for no maximum horizontal velocity.</td>
<td>-1</td>
</tr>
<tr>
<td>maximumVelocity.y</td>
<td>Maximum vertical velocity of the object (float or integer value). Negative value for no maximum horizontal velocity.</td>
<td>-1</td>
</tr>
<tr>
<td>acceleration.x</td>
<td>Horizontal acceleration in pixels/sec^2.</td>
<td>0</td>
</tr>
<tr>
<td>acceleration.y</td>
<td>Vertical acceleration in pixels/sec^2.</td>
<td>0</td>
</tr>
<tr>
<td>globalDrag</td>
<td>Deceleration applied when there is neither a horizontal nor a vertical acceleration until velocity reaches 0.</td>
<td>0</td>
</tr>
<tr>
<td>horizontalDrag</td>
<td>Horizontal deceleration applied when there is no horizontal acceleration until horizontal velocity reaches 0. So there could be a vertical acceleration while the horizontal drag is being applied.</td>
<td>0</td>
</tr>
<tr>
<td>verticalDrag</td>
<td>Vertical deceleration applied when there is no vertical acceleration until vertical velocity reaches 0. So there could be a horizontal acceleration while the vertical drag is being applied.</td>
<td>0</td>
</tr>
<tr>
<td>collidableSides</td>
<td>Tells which side can collide. A side that can't collide will let a collidable body pass through. The order of the list of booleans is "LEFT", "RIGHT", "TOP" and "BOTTOM". The value MUST be a string of 4 "0" and "1"'s.</td>
<td>1111</td>
</tr>
<tr>
<td>elasticity</td>
<td>Elasticity factor of the body, will determine how it should bounce in a collision. 0 means the body will not rebound at all when a collision is detected with another body. The body must be non-static for its elasticity to be applied. 1 would mean "perfect"
rebound. So if you set an elasticity of 1 to an object falling to
the ground, it would rebound at the same height infinitely. But, in reality, the elasticity calculation is not precise enough and it the height changes a bit each time.</td>
<td>0</td>
</tr>
<tr>
<td>staticBody</td>
<td>Wether or not the body will react to collisions. A static body will collide, but it won't be moved or affected by the collisions.</td>
<td>0</td>
</tr>
<tr>
<td>offset.x</td>
<td>Horizontal offset added to the position when detecting collisions.</td>
<td>0</td>
</tr>
<tr>
<td>offset.y</td>
<td>Vertical offset added to the position when detecting collisions.</td>
<td>0</td>
</tr>
<tr>
<td>collidingBoxRatio.x</td>
<td>Width of the colliding box compared to the body's actual width. To make the colliding box have half the body's width, you'd put 0.5 here.</td>
<td>1</td>
</tr>
<tr>
<td>collidingBoxRatio.y</td>
<td>Height of the colliding box compared to the body's actual height. To make the colliding box have half the body's height, you'd put 0.5 here.</td>
<td>1</td>
</tr>
<tr>
<td>offsetRatio</td>
<td>Wether or not the offset is a proportion of the body's size. False makes it so the offset is interpreted in pixels.</td>
<td>0</td>
</tr>
</table>

### Specific properties

#### RedBox::Sprite

The only difference a "RedBox::Sprite" has with a "RedBox::InanimateSprite" is the possibility to have animations. You can define animations for a sprite and the default animation. By default, a sprite doesn't have any animations and only one frame. 

For the frame property names "frame[i]", replace "i" with the index of the frame. The index starts at 0. So if you define "nbFrames" with 3, it'll expect definitions for "frame[0]", "frame[1]" and "frame[3]", else it'll use default values. At least one frame must be defined.

For animation definitions, it uses a similar idea as the frame definitions. You define animation properties with "animation[name]" where you replace "name" with the animation's name.

<table>
<tr>
<th>Name</th>
<th>Description</th>
<th>Default value</th>
</tr>
<tr>
<td>nbFrames</td>
<td>Number of frames the sprite has defined. Cannot be set to 0 (will be set to the default value if the number of frames is invalid).</td>
<td>1</td>
<td></td>
</tr>
<tr>
<td>frame[i].position.x</td>
<td>Horizontal position of the frame in the texture. Is only used for rectangle objects and polygon objects.</td>
<td>0</td>
</tr>
<tr>
<td>frame[i].position.y</td>
<td>Horizontal position of the frame in the texture. Is only used for rectangle objects and polygon objects.</td>
<td>0</td>
</tr>
<tr>
<td>frame[i].orientation</td>
<td>Orientation of the frame in the texture, used when the frame is rotated (for example, to save space in a texture atlas). The different possible values are "NORTH", "SOUTH", "EAST" and "WEST". The orientation represents the direction the top of the wanted frame image is pointing. For example, if the frame image is rotated 90 degrees clockwise, the orientation would be "EAST"</td>
<td>NORTH</td>
</tr>
<tr>
<td>animation[name].frames</td>
<td>The suit of frame indexes composing the animation. If an index is invalid, it will be interpreted as 0. The array is in the form "[0, 1, 4, 2, 2, 14, 5]" (surrounded by square brackets and frame indexes separated by comas, white spaces are all trimmed).</td>
<td>[0]</td>
</tr>
<tr>
<td>animation[name].timePerFrame</td>
<td>The time per frame (in seconds).</td>
<td>0.3</td>
</tr>
<tr>
<td>animation[name].nbLoops</td>
<td>Number of loops before the animation stops/finishes. Negative value for infinite looping.</td>
<td>-1</td>
</tr>
<tr>
<td>defaultAnimation</td>
<td>Name of the default animation. If this property is not defined, no animation is started and the default frame is displayed.</td>
<td></td>
</tr>
<tr>
<td>defaultFrame</td>
<td>Index of the frame to display by default if there is no default animation specified.</td>
<td>0</td>
</tr>
</table>

#### RedBox::InanimateSprite

A "RedBox::InanimateSprite" cannot be animated. It can only have one frame. Read the properties' description carefully, some of them can only be used for specific types of objects.
<table>
<tr>
<th>Name</th>
<th>Description</th>
<th>Default value</th>
</tr>
<tr>
<td>frame.position.x</td>
<td>Horizontal position of the frame in the texture. Only used for rectangle objects and polygon objects.</td>
<td>0</td>
</tr>
<tr>
<td>frame.position.y</td>
<td>Horizontal position of the frame in the texture. Only used for rectangle objects and polygon objects.</td>
<td>0</td>
</tr>
<tr>
<td>frame.orientation</td>
<td>Orientation of the frame in the texture, used when the frame is rotated (for example, to save space in a texture atlas). The different possible values are "NORTH", "SOUTH", "EAST" and "WEST". The orientation represents the direction the top of the wanted frame image is pointing. For example, if the frame image is rotated 90 degrees clockwise, the orientation would be "EAST".</td>
<td>NORTH</td>
</tr>
</table>
