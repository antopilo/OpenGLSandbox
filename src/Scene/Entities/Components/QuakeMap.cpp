#include "QuakeMap.h"

// Lib map stuff.
extern "C" {
#include "libmap/h/map_parser.h"
#include <libmap/h/geo_generator.h>
#include <libmap/h/surface_gatherer.h>
}

void QuakeMap::Draw()
{
    for (auto m : m_Meshes) {
        m.Draw();
    }
}
void QuakeMap::Load(std::string path)
{
	if (m_Path == path)
		return;

	m_Path = path;

	map_parser_load(m_Path.c_str());

	geo_generator_run();

	geo_generator_print_entities();

    for (int e = 0; e < entity_count; ++e)
    {
        entity* entity_inst = &entities[e];
        entity_geometry* entity_geo_inst = &entity_geo[e];
        printf("Entity %d\n", e);

        
        for (int b = 0; b < entity_inst->brush_count; ++b)
        {
            brush* brush_inst = &entity_inst->brushes[b];
            brush_geometry* brush_geo_inst = &entity_geo_inst->brushes[b];
            printf("Brush %d\n", b);

            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            int index_offset = 0;
            for (int f = 0; f < brush_inst->face_count; ++f)
            {
                face* face = &brush_inst->faces[f];
                texture_data* texture = &textures[face->texture_idx];
                face_geometry* face_geo_inst = &brush_geo_inst->faces[f];
                printf("Face %d\n", f);
                for (int i = 0; i < face_geo_inst->vertex_count; ++i)
                {   
                    face_vertex vertex = face_geo_inst->vertices[i];

                    vertices.push_back(Vertex{
                        glm::vec3(vertex.vertex.x * (1.0f / 64), vertex.vertex.z * (1.0f / 64), vertex.vertex.y * (1.0f / 64)),
                        glm::vec2(vertex.uv.u, vertex.uv.v),
                        glm::vec3(vertex.normal.x, vertex.normal.z, vertex.normal.y),
                        glm::vec3(vertex.tangent.x, vertex.tangent.z, vertex.tangent.y), glm::vec3(0.0, 1.0, 0.0), 0.0f
                        });
                    
                    printf("vertex: (%f %f %f), normal: (%f %f %f)\n",
                        vertex.vertex.x, vertex.vertex.y, vertex.vertex.z,
                        vertex.normal.x, vertex.normal.y, vertex.normal.z);
                }

                puts("Indices:");
                for (int i = 0; i < (face_geo_inst->vertex_count - 2) * 3; ++i)
                {
                    unsigned int index = face_geo_inst->indices[i];
                    printf("index: %d\n", index_offset + index);
                    indices.push_back(index_offset + (unsigned int)index);
                }
                
                index_offset += (face_geo_inst->vertex_count);
            }

            m_Meshes.push_back(Mesh(vertices, indices, new Material(glm::vec3(1, 0, 0))));
            putchar('\n');
            putchar('\n');
        }
    }
}

