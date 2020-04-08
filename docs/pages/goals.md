# Stretch Goals

This is a non-exhaustive list of potential goals that would be desireable to
work towards once the renderer is complected and functioning. Of course all of
these will be dependent on their performance impact, and their impact on the
readability of the code.

## Modernization/C++17

Much of the codebase of ``pbrt`` appears to use conventions that are longer
common place in modern c++ programming. For example there is significant usage
of ``C-arrays``, and in modern c++ it is preferred to use ``std::array`` when
possible. Then to return multiple values, it is now preferred to return a struct
or a tuple which contains the values instead of passing pointers as arguments.

There are a number of conventions such as these once, which would be nice to
change to modernize the code a bit more. And there are newer features that have
been introduced in C++17 that could be implemented to improve the existing
implementations.

## Optimizations

In a similar vain to the previous section, there are some optimizations that
could potentially be made. Most of which would actually improve the readability
of the code. With the introduction of ``constexpr`` whenever applicable, and
manually unwrapping the short loops, the code could become more readable, and
preform marginally better.

## Compartmentalization

Much of the code has been written in a single monolithic repository. It would
be beneficial to separate out different modules, so that they can be compiled
and changed independently to the main code base. For example much of the
``core/geometry`` directory does not have any dependence on other code in the
system, so it could be extracted into a separate repository, or a third party
repository could be used instead.

## OpenShadingLanguage

It would be intreating to implement
[OpenShadingLanguage](https://github.com/imageworks/openshadinglanguage), to
see if that can improve the performance, or simplify user interface. However, if
performance is hindered by the inclusion of this library, then it should be
removed.

## OpenColorIO

I don't know if this is applicable to a renderer, but it seems like it could be
worthwhile to look into further.

## OpenImageIO

It would be very nice to have one unified image input and output library,
instead of depending on multiple separate dependencies, each with their own
interface.

@note It would be nice to compartmentalize everything, and to implement
everything to the extent that the image writing library is able use our math
library, and our image representation.
