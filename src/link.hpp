#pragma once
#include "imnodes.h"


struct Link
{
    Link(int link_id,int source_id, int target_id)
    {
        id = link_id; 
        source_plug_id = source_id;
        target_plug_id = target_id;
    }

    void DrawLink()
    {
        ImNodes::Link(id, source_plug_id, target_plug_id);
    }

    int id;

    int source_plug_id;
    int target_plug_id;
};