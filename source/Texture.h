#pragma once
#include <GL/glew.h>
#include <vector>

class Texture {
public:
	Texture(int width, int height, GLenum format) :
		m_width{ width }, m_height{ height }, m_format{ format }
	{

	}
	int GetWidth() const {
		return m_width;
	}
	int GetHeight() const {
		return m_height;
	}
	//GL_RGBA8, GL_RGBA32F, GL_DEPTH_COMPONENT, GL_DEPTH24_STENCIL8
	GLenum GetImageFormat() const {
		return m_format;
	}
	GLuint GetHandle() const {
		return m_handle;
	}
	bool GetData(std::vector<float>& pixels) const {
		int size = m_width * m_height;
		if (m_format == GL_DEPTH_COMPONENT) {
			std::vector<float> textureData(size);
			const unsigned int handle = m_handle;

			glBindTexture(GL_TEXTURE_2D, handle);
			glGetTexImage(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, GL_FLOAT, textureData.data());
			glBindTexture(GL_TEXTURE_2D, 0);

			pixels = textureData;

			return true;
		}
		else if (m_format == GL_RGBA8) {

			std::vector<unsigned char> textureData(size * 4);
			glBindTexture(GL_TEXTURE_2D, m_handle);

			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data());
			glBindTexture(GL_TEXTURE_2D, 0);

			std::vector<float> pixelData(size);
			for (int i = 0; i < textureData.size(); i++) {
				float val = static_cast<float>(textureData[i] / 255.0f);
				pixelData[i] = val;
			}

			pixels = pixelData;

			return true;
		}
		else if (m_format == GL_RGBA32F) {

			std::vector<float> textureData(size * 4);
			glBindTexture(GL_TEXTURE_2D, m_handle);

			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, textureData.data());
			glBindTexture(GL_TEXTURE_2D, 0);

			pixels = textureData;

			return true;
		}
		// Can add other formats if needed.
		else {
			return false;
		}
	}
	void allocateVRAM() {
		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);
	GLenum internalFormat = GL_NONE;
	GLenum pixelFormat = GL_NONE;
	GLenum pixelDataType = GL_NONE;

  }
		//TODO

	}
private:
	GLuint m_handle;
	int m_width, m_height;
	GLenum m_format;

};
