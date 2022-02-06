# inspect shared_ptr
A shared_ptr implementation with inspection capabilities.

The idea is to provide a shared_ptr which allows you to inspect what parts of the code hold a shared_ptr to a resource. This can be
especially usefull if you expect a resource to be destroyed but some other entity still holds a shared_ptr to this resource. So this is somewhat like an memory sanitizer for shared_ptr.
