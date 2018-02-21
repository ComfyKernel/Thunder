#include "../../include/render/mesh.hpp"
#include "../../include/game.hpp"

#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

rn::mesh::mesh() { }

rn::mesh::mesh(void* vertices, size_t v_siz,
	       void* indices , size_t i_siz,
	       void* uvs     , size_t u_siz) {
  setBuffers(vertices, v_siz,
	     indices , i_siz,
	     uvs     , u_siz);
}

rn::mesh::mesh(const float3d& position,
	       const float3d& rotation,
	       const float3d& scale   ,
	       void* vertices, size_t v_siz,
	       void* indices , size_t i_siz,
	       void* uvs     , size_t u_siz) {
  setBuffers(vertices, v_siz,
	     indices , i_siz,
	     uvs     , u_siz);
  setTransform(position,
	       rotation,
	       scale   );
}

rn::mesh::mesh(const float3d& position,
	       const float3d& rotation,
	       const float3d& scale   ) {
  setTransform(position,
	       rotation,
	       scale   );
}

void rn::mesh::setBuffers(void* vertices, size_t v_siz,
			  void* indices , size_t i_siz,
			  void* uvs     , size_t u_siz) {
  buffers.vertex.create(vertices, v_siz,
			GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  buffers.uv.create    (uvs     , u_siz,
			GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  buffers.index.create (indices , i_siz,
			GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
  buffers.count = i_siz / sizeof(unsigned int);
}

void rn::mesh::setTransform(const float3d& position,
			    const float3d& rotation,
			    const float3d& scale   ) {
  transform.position = position;
  transform.rotation = rotation;
  transform.scale    = scale;
}

void rn::mesh::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, buffers.vertex);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0);
  
  glBindBuffer(GL_ARRAY_BUFFER, buffers.uv    );
  glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, (void*)0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.index);
}

void rn::mesh::draw() {
  glDrawElements(GL_TRIANGLES, buffers.count, GL_UNSIGNED_INT, (void*)0);
}

rn::mesh::~mesh() {
  buffers.vertex.destroy();
  buffers.index.destroy();
  buffers.uv.destroy();
}
