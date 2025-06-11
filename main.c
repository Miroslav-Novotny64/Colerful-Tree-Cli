#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define COLOR_RESET "\033[0m"
#define COLOR_DIR_ICON      "\033[38;5;39m"    // Bright blue for directories
#define COLOR_DIR_TEXT      "\033[38;5;159m"   // Light cyan for directory names
#define COLOR_SPECIAL_DIR   "\033[38;5;220m"   // Gold for special directories
#define COLOR_DEFAULT_ICON  "\033[38;5;245m"   // Gray for unknown files
// Document colors (warm tones)
#define COLOR_DOC_ICON      "\033[38;5;214m"   // Orange for documents
// Web development (cool blues/greens)
#define COLOR_WEB_ICON      "\033[38;5;51m"    // Cyan for web files
// Programming (vibrant colors)
#define COLOR_CODE_ICON     "\033[38;5;118m"   // Bright green for code
// Media (purple/magenta)
#define COLOR_IMAGE_ICON    "\033[38;5;207m"   // Bright magenta for images
// Archives (yellow/gold)
#define COLOR_ARCHIVE_ICON  "\033[38;5;226m"   // Bright yellow for archives
// System files (red)
#define COLOR_EXEC_ICON     "\033[38;5;196m"   // Bright red for executables
// Configuration (blue)
#define COLOR_CONFIG_ICON   "\033[38;5;75m"    // Light blue for config files
// Database (purple)
#define COLOR_DB_ICON       "\033[38;5;135m"   // Purple for databases
// Package/Build (orange)
#define COLOR_PACKAGE_ICON  "\033[38;5;208m"   // Orange for package files
// Git (red)
#define COLOR_GIT_ICON      "\033[38;5;196m"   // Red for git files



#define ICON_NODE_MODULES   "\ue71e"           // Node.js
#define ICON_SRC            "\uf07c"           // Source folder
#define ICON_DIST           "\uf1c0"           // Distribution/build
#define ICON_PUBLIC         "\uf0ac"           // Public/assets
#define ICON_COMPONENTS     "\ue7ba"           // React components
#define ICON_STYLES         "\ue749"           // CSS/Styles
#define ICON_IMAGES         "\uf03e"           // Images folder
#define ICON_DOCS           "\uf02d"           // Documentation
#define ICON_TESTS          "\uf0e7"           // Test files
#define ICON_GIT_FOLDER     "\ue702"           // Git folder
#define ICON_VSCODE         "\ue70c"           // VS Code
#define ICON_IDEA           "\ue7b5"           // IntelliJ IDEA
#define ICON_CONFIG_FOLDER  "\ue615"           // Config folder


#define ICON_README     "\uf48a"
#define ICON_LICENSE    "\uf718"
#define ICON_PDF        "\ueaeb"
#define ICON_TXT        ""
#define ICON_MD         "\ueeab"
#define ICON_XML        "󰗀"

// Directory and file icons
#define ICON_DIR        "\uf07b"
#define ICON_DEFAULT    "\uf15b"

#define ICON_HTML       "\ue736"
#define ICON_CSS        "\ue749"
#define ICON_SCSS       "\ue749"
#define ICON_SASS       "\ue74b"
#define ICON_LESS       "\ue758"
#define ICON_JS         "\uf2ef"
#define ICON_TS         "\ue8ca"
#define ICON_JSX        "\ue7ba"
#define ICON_TSX        "\ue7ba"
#define ICON_VUE        "\ufd42"
#define ICON_ANGULAR    "\ue753"
#define ICON_REACT      "\ue7ba"

#define ICON_C          "\ue61e"
#define ICON_CPP        "\ue61d"
#define ICON_PY         "\ue73c"
#define ICON_JAVA       "\ue738"
#define ICON_KOTLIN     "\ue634"
#define ICON_SWIFT      "\ufbe3"
#define ICON_DART       "\ue798"
#define ICON_PHP        "\ued6d"
#define ICON_RUBY       "\ueb48"
#define ICON_GO         "\ue627"
#define ICON_RUST       "\ue7a8"
#define ICON_LUA        "\ue620"
#define ICON_PERL       "\ue769"
#define ICON_R          "\uf25d"
#define ICON_MATLAB     "\ue61a"

#define ICON_BASH       "\uf489"
#define ICON_ZSH        "\uf489"
#define ICON_FISH       "\uf489"
#define ICON_POWERSHELL "\uf489"
#define ICON_BAT        "\uf17a"

#define ICON_SQL        "\uf1c0"
#define ICON_SQLITE     "\ue7c4"
#define ICON_DB         "\uf1c0"

#define ICON_PACKAGE    "\ue612"
#define ICON_NPM        "\ue71e"
#define ICON_YARN       "\ue718"
#define ICON_CARGO      "\ue7a8"
#define ICON_GRADLE     "\ue739"
#define ICON_MAVEN      "\ue739"
#define ICON_MAKEFILE   "\uf0ad"
#define ICON_CMAKE      "\uf0ad"
#define ICON_DOCKER     "\uf308"


// Media and archive icons
#define ICON_IMAGE      "\uf03e"
#define ICON_VIDEO      "\uf03d"
#define ICON_AUDIO      "\uf001"
#define ICON_ZIP        "󰛫"
#define ICON_EXE        "󰏋"

// Configuration and data icons
#define ICON_JSON       "󰘦"
#define ICON_YAML       "\uf481"
#define ICON_TOML       "\ue615"
#define ICON_CONFIG     "\ue615"
#define ICON_ENV        "\uf462"
#define ICON_LOG        "\uf4ed"
#define ICON_GIT_FILE   "\ue702"
#define ICON_YAML       "\uf481"
#define ICON_NINJA      "\ue64e"

typedef struct {
    const char* icon;
    const char* icon_color;
    const char* text_color;
} FileStyle;


FileStyle get_special_folder_style(const char* dirname) {
    if (strcmp(dirname, "node_modules") == 0) return (FileStyle){ICON_NODE_MODULES, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "src") == 0 || strcmp(dirname, "source") == 0) return (FileStyle){ICON_SRC, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "dist") == 0 || strcmp(dirname, "build") == 0 || strcmp(dirname, "out") == 0) return (FileStyle){ICON_DIST, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "public") == 0 || strcmp(dirname, "assets") == 0 || strcmp(dirname, "static") == 0) return (FileStyle){ICON_PUBLIC, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "components") == 0 || strcmp(dirname, "component") == 0) return (FileStyle){ICON_COMPONENTS, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "styles") == 0 || strcmp(dirname, "css") == 0 || strcmp(dirname, "scss") == 0) return (FileStyle){ICON_STYLES, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "js") == 0 || strcmp(dirname, "javascript") == 0 || strcmp(dirname, "scripts") == 0) return (FileStyle){ICON_JS, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "images") == 0 || strcmp(dirname, "img") == 0 || strcmp(dirname, "imgs") == 0) return (FileStyle){ICON_IMAGES, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "fonts") == 0 || strcmp(dirname, "font") == 0) return (FileStyle){"\uf031", COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "docs") == 0 || strcmp(dirname, "documentation") == 0 || strcmp(dirname, "doc") == 0) return (FileStyle){ICON_DOCS, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "tests") == 0 || strcmp(dirname, "test") == 0 || strcmp(dirname, "__tests__") == 0) return (FileStyle){ICON_TESTS, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, ".git") == 0) return (FileStyle){ICON_GIT_FOLDER, COLOR_GIT_ICON, COLOR_DIR_TEXT};
    if (strcmp(dirname, ".vscode") == 0) return (FileStyle){ICON_VSCODE, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, ".idea") == 0) return (FileStyle){ICON_IDEA, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};
    if (strcmp(dirname, "config") == 0 || strcmp(dirname, "configs") == 0 || strcmp(dirname, ".config") == 0) return (FileStyle){ICON_CONFIG_FOLDER, COLOR_SPECIAL_DIR, COLOR_DIR_TEXT};

    return (FileStyle){ICON_DIR, COLOR_DIR_ICON, COLOR_DIR_TEXT};
}

FileStyle get_file_style(const char* filename) {
    // Check for special files without extensions first
    if (strcmp(filename, "README") == 0 || strncmp(filename, "README.", 7) == 0) return (FileStyle){ICON_README, COLOR_DOC_ICON, COLOR_RESET};
    if (strcmp(filename, "LICENSE") == 0 || strcmp(filename, "LICENCE") == 0) return (FileStyle){ICON_LICENSE, COLOR_DOC_ICON, COLOR_RESET};
    if (strcmp(filename, "Makefile") == 0 || strcmp(filename, "makefile") == 0) return (FileStyle){ICON_MAKEFILE, COLOR_PACKAGE_ICON, COLOR_RESET};
    if (strcmp(filename, "CMakeLists.txt") == 0) return (FileStyle){ICON_CMAKE, COLOR_PACKAGE_ICON, COLOR_RESET};
    if (strcmp(filename, "Dockerfile") == 0 || strcmp(filename, "dockerfile") == 0) return (FileStyle){ICON_DOCKER, COLOR_PACKAGE_ICON, COLOR_RESET};
    if (strcmp(filename, "package.json") == 0) return (FileStyle){ICON_NPM, COLOR_PACKAGE_ICON, COLOR_RESET};
    if (strcmp(filename, "yarn.lock") == 0) return (FileStyle){ICON_YARN, COLOR_PACKAGE_ICON, COLOR_RESET};
    if (strcmp(filename, "Cargo.toml") == 0 || strcmp(filename, "Cargo.lock") == 0) return (FileStyle){ICON_CARGO, COLOR_PACKAGE_ICON, COLOR_RESET};
    if (strcmp(filename, ".gitignore") == 0 || strcmp(filename, ".gitconfig") == 0) return (FileStyle){ICON_GIT_FILE, COLOR_GIT_ICON, COLOR_RESET};

    const char* ext = strrchr(filename, '.');
    if (!ext) return (FileStyle){ICON_DEFAULT, COLOR_DEFAULT_ICON, COLOR_RESET};

    ext++; // Skip the dot

    // In get_file_style function, make sure this line exists:
    if (strcmp(ext, "yaml") == 0 || strcmp(ext, "yml") == 0) return (FileStyle){ICON_YAML, COLOR_CONFIG_ICON, COLOR_RESET};
    if (strcmp(filename, "build.ninja") == 0 || strcmp(filename, "rules.ninja") == 0) return (FileStyle){ICON_NINJA, COLOR_PACKAGE_ICON, COLOR_RESET};
    if (strcmp(filename, "CMakeCache.txt") == 0) return (FileStyle){ICON_CMAKE, COLOR_PACKAGE_ICON, COLOR_RESET};
    if (strcmp(filename, "cmake_install.cmake") == 0) return (FileStyle){ICON_CMAKE, COLOR_PACKAGE_ICON, COLOR_RESET};
    if (strstr(filename, "cmake") != NULL && strcmp(ext, "cmake") == 0) return (FileStyle){ICON_CMAKE, COLOR_PACKAGE_ICON, COLOR_RESET};
    if (strcmp(filename, "tree.iml") == 0 || strstr(filename, ".iml") != NULL) return (FileStyle){ICON_IDEA, COLOR_CONFIG_ICON, COLOR_RESET};


    // Document files
    if (strcmp(ext, "pdf") == 0) return (FileStyle){ICON_PDF, COLOR_DOC_ICON, COLOR_RESET};
    if (strcmp(ext, "txt") == 0) return (FileStyle){ICON_TXT, COLOR_DOC_ICON, COLOR_RESET};
    if (strcmp(ext, "md") == 0 || strcmp(ext, "markdown") == 0) return (FileStyle){ICON_MD, COLOR_DOC_ICON, COLOR_RESET};
    if (strcmp(ext, "xml") == 0) return (FileStyle){ICON_XML, COLOR_DOC_ICON, COLOR_RESET};

    // Web development
    if (strcmp(ext, "html") == 0 || strcmp(ext, "htm") == 0) return (FileStyle){ICON_HTML, COLOR_WEB_ICON, COLOR_RESET};
    if (strcmp(ext, "css") == 0) return (FileStyle){ICON_CSS, COLOR_WEB_ICON, COLOR_RESET};
    if (strcmp(ext, "scss") == 0) return (FileStyle){ICON_SCSS, COLOR_WEB_ICON, COLOR_RESET};
    if (strcmp(ext, "sass") == 0) return (FileStyle){ICON_SASS, COLOR_WEB_ICON, COLOR_RESET};
    if (strcmp(ext, "less") == 0) return (FileStyle){ICON_LESS, COLOR_WEB_ICON, COLOR_RESET};
    if (strcmp(ext, "js") == 0) return (FileStyle){ICON_JS, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "jsx") == 0) return (FileStyle){ICON_JSX, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "ts") == 0) return (FileStyle){ICON_TS, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "tsx") == 0) return (FileStyle){ICON_TSX, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "vue") == 0) return (FileStyle){ICON_VUE, COLOR_CODE_ICON, COLOR_RESET};

    // Programming languages
    if (strcmp(ext, "c") == 0 || strcmp(ext, "h") == 0) return (FileStyle){ICON_C, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "cpp") == 0 || strcmp(ext, "cc") == 0 || strcmp(ext, "cxx") == 0 || strcmp(ext, "hpp") == 0) return (FileStyle){ICON_CPP, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "py") == 0) return (FileStyle){ICON_PY, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "java") == 0) return (FileStyle){ICON_JAVA, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "kt") == 0 || strcmp(ext, "kts") == 0) return (FileStyle){ICON_KOTLIN, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "swift") == 0) return (FileStyle){ICON_SWIFT, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "dart") == 0) return (FileStyle){ICON_DART, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "php") == 0) return (FileStyle){ICON_PHP, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "rb") == 0) return (FileStyle){ICON_RUBY, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "go") == 0) return (FileStyle){ICON_GO, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "rs") == 0) return (FileStyle){ICON_RUST, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "lua") == 0) return (FileStyle){ICON_LUA, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "pl") == 0 || strcmp(ext, "pm") == 0) return (FileStyle){ICON_PERL, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "r") == 0 || strcmp(ext, "R") == 0) return (FileStyle){ICON_R, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "m") == 0) return (FileStyle){ICON_MATLAB, COLOR_CODE_ICON, COLOR_RESET};

    // Shell scripts
    if (strcmp(ext, "sh") == 0) return (FileStyle){ICON_BASH, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "bash") == 0) return (FileStyle){ICON_BASH, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "zsh") == 0) return (FileStyle){ICON_ZSH, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "fish") == 0) return (FileStyle){ICON_FISH, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "ps1") == 0) return (FileStyle){ICON_POWERSHELL, COLOR_CODE_ICON, COLOR_RESET};
    if (strcmp(ext, "bat") == 0 || strcmp(ext, "cmd") == 0) return (FileStyle){ICON_BAT, COLOR_CODE_ICON, COLOR_RESET};

    // Database files
    if (strcmp(ext, "sql") == 0) return (FileStyle){ICON_SQL, COLOR_DB_ICON, COLOR_RESET};
    if (strcmp(ext, "sqlite") == 0 || strcmp(ext, "sqlite3") == 0 || strcmp(ext, "db") == 0) return (FileStyle){ICON_SQLITE, COLOR_DB_ICON, COLOR_RESET};

    // Configuration files
    if (strcmp(ext, "json") == 0) return (FileStyle){ICON_JSON, COLOR_CONFIG_ICON, COLOR_RESET};
    if (strcmp(ext, "yaml") == 0 || strcmp(ext, "yml") == 0) return (FileStyle){ICON_YAML, COLOR_CONFIG_ICON, COLOR_RESET};
    if (strcmp(ext, "toml") == 0) return (FileStyle){ICON_TOML, COLOR_CONFIG_ICON, COLOR_RESET};
    if (strcmp(ext, "ini") == 0 || strcmp(ext, "cfg") == 0 || strcmp(ext, "conf") == 0 || strcmp(ext, "config") == 0) return (FileStyle){ICON_CONFIG, COLOR_CONFIG_ICON, COLOR_RESET};
    if (strcmp(ext, "env") == 0) return (FileStyle){ICON_ENV, COLOR_CONFIG_ICON, COLOR_RESET};
    if (strcmp(ext, "log") == 0) return (FileStyle){ICON_LOG, COLOR_CONFIG_ICON, COLOR_RESET};

    // Media files
    if (strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0 || strcmp(ext, "png") == 0 ||
        strcmp(ext, "gif") == 0 || strcmp(ext, "bmp") == 0 || strcmp(ext, "svg") == 0 ||
        strcmp(ext, "webp") == 0 || strcmp(ext, "ico") == 0) return (FileStyle){ICON_IMAGE, COLOR_IMAGE_ICON, COLOR_RESET};
    if (strcmp(ext, "mp4") == 0 || strcmp(ext, "avi") == 0 || strcmp(ext, "mkv") == 0 ||
        strcmp(ext, "mov") == 0 || strcmp(ext, "wmv") == 0 || strcmp(ext, "webm") == 0) return (FileStyle){ICON_VIDEO, COLOR_IMAGE_ICON, COLOR_RESET};
    if (strcmp(ext, "mp3") == 0 || strcmp(ext, "wav") == 0 || strcmp(ext, "flac") == 0 ||
        strcmp(ext, "ogg") == 0 || strcmp(ext, "m4a") == 0) return (FileStyle){ICON_AUDIO, COLOR_IMAGE_ICON, COLOR_RESET};

    // Archives
    if (strcmp(ext, "zip") == 0 || strcmp(ext, "tar") == 0 || strcmp(ext, "gz") == 0 ||
        strcmp(ext, "rar") == 0 || strcmp(ext, "7z") == 0 || strcmp(ext, "bz2") == 0 ||
        strcmp(ext, "xz") == 0) return (FileStyle){ICON_ZIP, COLOR_ARCHIVE_ICON, COLOR_RESET};

    // Executables
    if (strcmp(ext, "exe") == 0 || strcmp(ext, "bin") == 0 || strcmp(ext, "run") == 0 ||
        strcmp(ext, "app") == 0) return (FileStyle){ICON_EXE, COLOR_EXEC_ICON, COLOR_RESET};

    return (FileStyle){ICON_DEFAULT, COLOR_DEFAULT_ICON, COLOR_RESET};
}

void print_tree(const char *path, int level) {
    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        for (int i = 0; i < level; i++) printf("  ");

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        stat(fullpath, &st);

        if (S_ISDIR(st.st_mode)) {
            FileStyle style = get_special_folder_style(entry->d_name);
            printf("%s%s%s %s%s%s\n", style.icon_color, style.icon, COLOR_RESET,
                   style.text_color, entry->d_name, COLOR_RESET);
            print_tree(fullpath, level + 1);
        } else {
            FileStyle style = get_file_style(entry->d_name);
            printf("%s%s%s %s%s%s\n", style.icon_color, style.icon, COLOR_RESET,
                   style.text_color, entry->d_name, COLOR_RESET);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *path = argc > 1 ? argv[1] : ".";
    print_tree(path, 0);
    return 0;
}