################################################################################
#
# kvpstorage CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D)
#
################################################################################

KVPSTORAGE_VERSION = 1.0
KVPSTORAGE_SITE = ./src #./package/kvpstorage/src
KVPSTORAGE_SITE_METHOD = local
# KVPSTORAGE_LICENSE = BSD-3-Clause
# KVPSTORAGE_LICENSE_FILE = LICENSE


define KVPSTORAGE_BUILD_CMDS
    $(MAKE)
endef

define KVPSTORAGE_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/kvpstorage $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))