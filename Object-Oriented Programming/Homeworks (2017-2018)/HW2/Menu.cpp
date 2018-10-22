#include"Menu.h"

int menu(int argc, char* argv)
{
	if (argc == 1)
	{
		std::cout << "The file path was not input!";
		return 1;
	}
	else
	{
		Text text;
		char command_input[MAX_INPUT_SIZE];
		if (text.loadTextFromFile(argv))
		{
			do
			{
				std::cout << "Type a command!\n";
				std::cin >> std::setw(MAX_INPUT_SIZE) >> command_input;

				if (!strcmp(command_input, "makeHeading"))
				{
					size_t num = 0;
					std::cin >> num;
					if (!num)
					{
						std::cout << "Invalid input!\n";
						continue;
					}
					text.makeHeading(num);
				}

				if (!strcmp(command_input, "makeItalic"))
				{
					size_t line = 0, from = 0, to = 0;
					std::cin >> line >> from >> to;
					if (!line || !from || !to)
					{
						std::cout << "Invalid input!\n";
						continue;
					}
					text.putStars(ITALIC, line, from, to);
				}

				if (!strcmp(command_input, "makeBold"))
				{
					size_t line = 0, from = 0, to = 0;
					std::cin >> line >> from >> to;
					if (!line || !from || !to)
					{
						std::cout << "Invalid input!\n";
						continue;
					}
					text.putStars(BOLD, line, from, to);
				}

				if (!strcmp(command_input, "makeCombine"))
				{
					size_t line = 0, from = 0, to = 0;
					std::cin >> line >> from >> to;
					if (!line || !from || !to)
					{
						std::cout << "Invalid input!\n";
						continue;
					}
					text.putStars(COMBINED, line, from, to);
				}

				if (!strcmp(command_input, "addLine"))
				{
					char buff[MAX_LINE_SIZE];
					std::cin.getline(buff, MAX_LINE_SIZE);
					text.addNewLine(buff);
				}

				if (!strcmp(command_input, "remove"))
				{
					size_t line = 0;
					std::cin >> line;
					if (!line)
					{
						std::cout << "Invalid input!\n";
						continue;
					}
					text.removeLine(line);
				}

				std::cout << std::endl;

			} while (strcmp(command_input, "quit"));

			text.printArr();

			if (text.saveTextToFile(argv)) std::cout << "\nChanges were successfully saved!";
			else std::cout << "\nCould not save changes!";
			return 0;
		}
		else std::cout << "\nThe file could not be opened!";
		return 1;
	}
}