/*
 * This file is part of budgie-desktop
 *
 * Copyright © 2015-2017 Ikey Doherty <ikey@solus-project.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _BudgiePanelManager BudgiePanelManager;
typedef struct _BudgiePanelManagerClass BudgiePanelManagerClass;

struct _BudgiePanelManagerClass {
        GObjectClass parent_class;
};

/**
 * BudgiePanelManager is the main life cycle of the Budgie Panel program,
 * monitoring various settings and controlling the lifetime of each Budgie Panel
 * instance (i.e. the BudgiePanel windows)
 */
struct _BudgiePanelManager {
        GObject parent;
};

#define BUDGIE_TYPE_PANEL_MANAGER budgie_panel_manager_get_type()
#define BUDGIE_PANEL_MANAGER(o)                                                                    \
        (G_TYPE_CHECK_INSTANCE_CAST((o), BUDGIE_TYPE_PANEL_MANAGER, BudgiePanelManager))
#define BUDGIE_IS_PANEL_MANAGER(o) (G_TYPE_CHECK_INSTANCE_TYPE((o), BUDGIE_TYPE_PANEL_MANAGER))
#define BUDGIE_PANEL_MANAGER_CLASS(o)                                                              \
        (G_TYPE_CHECK_CLASS_CAST((o), BUDGIE_TYPE_PANEL_MANAGER, BudgiePanelManagerClass))
#define BUDGIE_IS_PANEL_MANAGER_CLASS(o) (G_TYPE_CHECK_CLASS_TYPE((o), BUDGIE_TYPE_PANEL_MANAGER))
#define BUDGIE_PANEL_MANAGER_GET_CLASS(o)                                                          \
        (G_TYPE_INSTANCE_GET_CLASS((o), BUDGIE_TYPE_PANEL_MANAGER, BudgiePanelManagerClass))

GType budgie_panel_manager_get_type(void);

/**
 * Construct a new BudgiePanelManager
 */
BudgiePanelManager *budgie_panel_manager_new(void);

G_END_DECLS

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
