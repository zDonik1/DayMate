import QtQuick 2.0

import Felgo 3.0

import "model"
import "logic"
import "pages"
import "helper"

App {
    // business logic
    Logic {
        id: logic
    }

    // view
    Navigation {
        id: navigation

        // first tab
        NavigationItem {
            title: qsTr("Todo List")
            icon: IconType.list

            NavigationStack {
                splitView: tablet // use side-by-side view on tablets
                initialPage: TodoListPage { }
            }
        }
    }
}
