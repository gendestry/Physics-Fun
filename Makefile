# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),release)
  glfw_config = release
  glad_config = release
  imgui_config = release
  PhysicsFun_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := glfw glad imgui PhysicsFun

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

glfw:
ifneq (,$(glfw_config))
	@echo "==== Building glfw ($(glfw_config)) ===="
	@${MAKE} --no-print-directory -C dependencies/glfw -f Makefile config=$(glfw_config)
endif

glad:
ifneq (,$(glad_config))
	@echo "==== Building glad ($(glad_config)) ===="
	@${MAKE} --no-print-directory -C dependencies/glad -f Makefile config=$(glad_config)
endif

imgui:
ifneq (,$(imgui_config))
	@echo "==== Building imgui ($(imgui_config)) ===="
	@${MAKE} --no-print-directory -C dependencies/imgui -f Makefile config=$(imgui_config)
endif

PhysicsFun: glfw glad imgui
ifneq (,$(PhysicsFun_config))
	@echo "==== Building PhysicsFun ($(PhysicsFun_config)) ===="
	@${MAKE} --no-print-directory -C PhysicsFun -f Makefile config=$(PhysicsFun_config)
endif

clean:
	@${MAKE} --no-print-directory -C dependencies/glfw -f Makefile clean
	@${MAKE} --no-print-directory -C dependencies/glad -f Makefile clean
	@${MAKE} --no-print-directory -C dependencies/imgui -f Makefile clean
	@${MAKE} --no-print-directory -C PhysicsFun -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   glfw"
	@echo "   glad"
	@echo "   imgui"
	@echo "   PhysicsFun"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"