#include <gtest/gtest.h>
#include "../inc/GameMap.hpp"

TEST(GameMap, ValidSimpleFile) {

}

TEST(GameMap, ValidMultiTabFile) {

}

TEST(GameMap, InvalidSimpleFile) {

}

TEST(GameMap, InvalidNoTexture) {

}

TEST(GameMap, InvalidWrongColor) {

}

TEST(GameMap, InvalidMissingColors) {

}

TEST(GameMap, InvalidUnclosedMap) {

}

TEST(GameMap, InvalidNoMap) {

}

TEST(GameMap, NonExistentTextures) {

}

TEST(GameMap, FileNonExistent) {
	EXPECT_THROW(GameMap gm("nonexistent_file.cub"), std::runtime_error);
	EXPECT_THROW(GameMap gm("erjkfhfiuhru"), std::runtime_error);
}

