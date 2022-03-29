################################################################################
#
# kvpstorage
#
################################################################################

KVPSTORAGE_VERSION = 1.0
KVPSTORAGE_SITE = ./package/hello/src
KVPSTORAGE_SITE_METHOD = local

define KVPSTORAGE_BUILD_CMDS
    $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D)
endef

define HELLO_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/hello $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))