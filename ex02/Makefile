NAME := array

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic
RM := rm -rf

SRCS := main.cpp 
OBJDIR := obj
DEPDIR := dep
OBJS := $(addprefix $(OBJDIR)/,$(SRCS:.cpp=.o))
DEPS := $(addprefix $(DEPDIR)/,$(SRCS:.cpp=.d))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR) $(DEPDIR):
	mkdir -p $@

$(OBJDIR)/%.o: %.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(DEPDIR)/$*.d -c $< -o $@

clean:
	$(RM) $(OBJDIR) $(DEPDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

-include $(DEPS)

.PHONY: all clean fclean re