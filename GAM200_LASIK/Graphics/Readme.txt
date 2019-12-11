Graphic Engine Readme

- Displaying object
	> Shader, Mesh, Vertices are required. Texture is required when the object has an image.
	> Shader should be loaded from .vert and .frag files (shape, texture, animation).
	> Vertices should be initialize with mesh and vertices description.
	> When the object has texture, mesh should be rectangle, 
	  layout should be Point & Texture Coordinate.
	> Texture should load an image.
	> Transform needed when object should be moved.

- Example of initializing
-----------------------------------
	Shader shader;
	Mesh mesh;
	Vertices vertices;
	VerticesDescription layout{ VerticesDescription::Type::Point,
								VerticesDescription::Type::TextureCoordinate };
	Texture texture;
	Transform transform;
------------------------------------
	shader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);

	mesh = MESH::create_rectangle({ 0.0f }, { 1.0f }, { 0.0f });
	// Position, size, color
	vertices.InitializeWithMeshAndLayout(rectangle, layout);
	texture.LoadFromPath(somepng);
	dragoneTransform.SetTranslation({ 100.0f, 0.0f });
------------------------------------
	In this example, it loads shader, create mesh, initialize vertices.
	Loading texture, move this to { 100.0f, 0.0f }.

- Example of updating
------------------------------------
	ndc = CameraToNDC * WorldToCamera * ModelToWorld;
	Draw::draw({ shader, vertices, ndc, texture });
------------------------------------
