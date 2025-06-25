#include <gtest/gtest.h>
#include "../inc/GameMap.hpp"

TEST(GameMap, ValidSimpleFile) {
	EXPECT_NO_THROW(GameMap gm("../testmaps/validSimple.cub"));
}

TEST(GameMap, ValidMultiTabFile) {
	EXPECT_NO_THROW(GameMap gm("../testmaps/validMultiTab.cub"));
}

TEST(GameMap, ValidComplexFile) {
	EXPECT_NO_THROW(GameMap gm("../testmaps/validComplex.cub"));
}

TEST(GameMap, InvalidSimpleFile) {
	EXPECT_THROW(GameMap gm("../testmaps/InvalidSimple.cub"), std::runtime_error);
}

TEST(GameMap, InvalidNoTexture) {
	EXPECT_THROW(GameMap gm("../testmaps/InvalidNoTexture.cub"), std::runtime_error);
}

TEST(GameMap, InvalidWrongColor) {
	EXPECT_THROW(GameMap gm("../testmaps/InvalidWrongColor.cub"), std::invalid_argument);
}

TEST(GameMap, InvalidMissingColors) {
	EXPECT_THROW(GameMap gm("../testmaps/InvalidMissingColors.cub"), std::runtime_error);
}

TEST(GameMap, InvalidUnclosedMap) {
	EXPECT_THROW(GameMap gm("../testmaps/UnclosedMap.cub"), std::runtime_error);
}

TEST(GameMap, InvalidNoMap) {
	EXPECT_THROW(GameMap gm("../testmaps/InvalidNoMap.cub"), std::runtime_error);
}

TEST(GameMap, FileNonExistent) {
	EXPECT_THROW(GameMap gm("nonexistent_file.cub"), std::runtime_error);
	EXPECT_THROW(GameMap gm("erjkfhfiuhru"), std::runtime_error);
}

