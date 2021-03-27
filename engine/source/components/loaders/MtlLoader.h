//
// Created by moonlin on 25.03.2021.
//

#ifndef OGL3DG_MTLLOADER_H
#define OGL3DG_MTLLOADER_H

#include <map>
#include <fstream>
#include "components/initals/Material.h"

class MtlLoader {
public:
    static std::map<std::string, SurfaceStruct *> loadMtlFromFile(const char *path);
};


#endif //OGL3DG_MTLLOADER_H
