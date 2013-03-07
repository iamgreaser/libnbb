libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).

Note, files in dat/ are of dubious origin.
I don't know who originally made the rainbow clown image.

-------------------------------------------------------------------------------

What is libnbb?

Nothing but blits. Well, also colour conversions. But those are for blits.

What can it do?

Blit stuff in a multitude of specific formats.

TODO: make this so.
Currently it only does same-format blits for simple byte-aligned formats.
Such as BGRX 8bpc.
Also doesn't do alpha blending or magic colour transparency yet.

What can't it do?

Blit to CGA/EGA in a single call.
You'll have to handle the interlacing crap / linear crap yourself.
A palette might help.

It also can't set video modes or open windows for you.
Video modes aren't blits. Neither are windows. But they accept blits.

It can't load images for you.
If you want to roll your own loader, I recommend the .tga format.
The cheats' method is to know the format / size, skip 18 bytes, and load,
which is precisely what happens in testapp.c.

-------------------------------------------------------------------------------

API docs:

TODO. Use at your own risk.

-------------------------------------------------------------------------------

Coding conventions:

Hard tabs only. If you use soft tabs, I will break your face.

If in doubt, follow Allman style.

if-elseif-else follows this:
	if ()
	{
		foo();
	} else if () {
		bar();
	} else {
		baz();
	}

All braces are optional.

Only include what you absolutely MUST. It keeps compile times down.

All .c files must be kept under 100 lines! If it gets too big, split it.
I can accept an oversize file in the repo, but it will need to be split soon.

Files must end with a newline.

All functions must be documented in the source.
Currently we're not following doxygen standards... that MIGHT change, though.
You CAN use doxygen standards if you want.

If you get any warnings, fix them.
We've turned this challenge up to 11. Have fun.

