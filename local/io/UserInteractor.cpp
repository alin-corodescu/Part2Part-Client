//
// Created by alin on 12/21/16.
//
#pragma once
#include "UserInteractor.h"
#include "CLI.h"


UserInteractor *UserInteractor::getInstance() {
    if (instance == NULL) {
        if (type == CMD)
            instance = new CLI();
        if (type == GUI)
            ;
    }

    return instance;
}
