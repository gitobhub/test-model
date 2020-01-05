#include "Json.h"
#include "Input.h"

void Input::Build(const std::string& name, const Input* root) const
{
    pStore_.reset(new Json(name, (root ? root->pStore_.get() : nullptr)));
}
