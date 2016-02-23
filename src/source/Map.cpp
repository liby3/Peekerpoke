#include "../include/Map.h"

Map::Map() {
	initial();
}

Map::~Map() {}

void Map::init_matrix() {
	/* set the whole map obstacle */
	memset(matrix, 1, sizeof(matrix));
	/* set the avilable positions */
	for (int i = 0; i < MAP_ROWS; i++) {
		matrix[i][4] = 0;
	}
	for (int i = 0; i < MAP_COLUMNS; i++) {
		matrix[4][i] = 0;
	}
}

void Map::init_destination() {
	destination = point(0, 4);
}

void Map::initial() {
	init_matrix();
	init_destination();
}

void Map::print() {
	printf("Current map:\n");
	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLUMNS; j++) {
			printf("%d \n", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void Map::init_dfs() {
	memset(visited, false, sizeof(visited));
	visited[currentPosition.x][currentPosition.y] = true;
	currentPosition.step = 1;
}

bool Map::dfs_point_valid(const point& p) {
	if (!(p.x >= 0 && p.x < MAP_ROWS)) {
		return false;
	} else if (!(p.y >= 0 && p.y < MAP_COLUMNS)) {
		return false;
	} else if (visited[p.x][p.y]) {
		return false;
	} else if (matrix[p.x][p.y] != 0) {
		return false;
	}
	return true;
}

void Map::print_path(int length) {
	for (int i = 0; i < length; i++) {
		printf("(%d, %d)\n", path[i].x, path[i].y);
	}
	printf("\n\n");
}

bool Map::dfs(point cur, int step) {
	if (cur == destination) {
		print_path(step);
		return true;
	} else {
		point p;
		for (int i = 0; i < 4; i++) {
			p.x = cur.x + oper_x[i];
			p.y = cur.y + oper_y[i];
			if (dfs_point_valid(p)) {
				path[step] = p;
				p.step = cur.p + 1;
				visited[p.x][p.y] = true;
				if (dfs(p, step + 1)) {
					return true;
				}
			}
		}
	}
	return false;
}

void Map::update_next_position() {
	init_dfs();
	if (dfs(currentPosition, 0)) {
		nextPosition = path[0];
	} else {
		printf("NO ROUTE!\n");
		nextPosition = point(0, 0);
	}
}

bool Map::next_position_avilable() {
	return (matrix[nextPosition.x][nextPosition.y] == 0);
}

direction get_current_direction() {
	return _currentDirection;
}

void Map::set_current_direction(direction _currentDirection) {
	currentDirection = _currentDirection;
}

int Map::compare_current2next_direction(char axis) {
	if (axis == 'x') {
		if (currentPosition.x == nextPosition.x) {
			return 0;
		} else if (currentPosition.x > nextPosition.x) {
			return 1;
		} else {
			return -1;
		}
	} else {
		if (currentPosition.y == nextPosition.y) {
			return 0;
		} else if (currentPosition.y > nextPosition.y) {
			return 1;
		} else {
			return -1;
		}
	}
	return 0;
}