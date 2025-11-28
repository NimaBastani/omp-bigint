# BigInt Component/Plugin for open.mp and SA:MP

A lightweight component/plugin that adds signed 64-bit integer support to Pawn scripts for both **open.mp** and **SA:MP** servers. It exposes a `BigInt` tag plus a collection of arithmetic, conversion, and comparison natives so game-mode authors can safely store counters such as bank balances, experience totals, and economy statistics without overflowing the default 32-bit cell size.

> **Note:** SA:MP plugin support was added by [NimaBastani](https://github.com/NimaBastani).

## Building

### Prerequisites

- CMake 3.19 or higher
- C++17 compatible compiler
- For open.mp: open.mp SDK (included in `deps/omp-sdk`)
- For SA:MP: Pawn AMX library (included in `deps/pawn`) and SA:MP plugin SDK (included in `deps/samp-plugin-sdk`)

### Building for open.mp (default)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

The component will be built as `omp-bigint.dll` (Windows) or `omp-bigint.so` (Linux).

### Building for SA:MP

**Windows (32-bit):**
```bash
cmake -B build -S . -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DBUILD_SAMP_PLUGIN=ON -A Win32
cmake --build build
```

**Windows (64-bit):**
```bash
cmake -B build -S . -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DBUILD_SAMP_PLUGIN=ON
cmake --build build
```

**Linux:**
```bash
cmake -B build -S . -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DBUILD_SAMP_PLUGIN=ON
cmake --build build
```

The plugin will be built as `samp-bigint.dll` (Windows) or `samp-bigint.so` (Linux).

## Installation

### For open.mp

1. Visit the **Releases** page of this repository and download the archive or binary that matches your server platform (Windows `.dll`, Linux `.so`).
2. Extract the download and copy the component file into your open.mp server `components/` directory.
3. Copy `omp_bigint.inc` into the include directory used by your Pawn compiler (e.g., `gamemodes/include/`).
4. Add `#include <omp_bigint>` to any script that needs the BigInt natives and rebuild your Pawn scripts.

### For SA:MP

1. Visit the **Releases** page of this repository and download the SA:MP plugin binary that matches your server platform (Windows `.dll`, Linux `.so`).
2. Copy the plugin file into your SA:MP server `plugins/` directory.
3. Add the plugin to your `server.cfg`:
   ```
   plugins samp-bigint
   ```
   (On Windows, use `plugins samp-bigint.dll`; on Linux, use `plugins samp-bigint.so`)
4. Copy `omp_bigint.inc` into the include directory used by your Pawn compiler (e.g., `pawno/include/`).
5. Add `#include <omp_bigint>` to any script that needs the BigInt natives and rebuild your Pawn scripts.

## Usage

The include defines the `BigInt` tag plus helpers such as `new_bigint`, `BigInt_SetInt`, and the arithmetic/compare natives. A quick example that tracks per-player bank balances:

```pawn
#include <omp_bigint>

new_bigint(g_BankBalance[MAX_PLAYERS]);

/*
 Or if you want to use the common way of creating variables:
 
     new BigInt:g_BankBalance[MAX_PLAYERS][eBigIntParts];

     new BigInt:TestVar[eBigIntParts];
 or
     new_bigint(TestVar);

 or in your enum:
     enum PLAYER_DATA
     {
        ...
        BigInt:BankMoney[eBigIntParts],
        ...
     };
*/
 

public OnPlayerConnect(playerid)
{
    BigInt_SetInt(g_BankBalance[playerid], 0);
}

stock BankDeposit(playerid, amount)
{
    BigInt_AddInt(g_BankBalance[playerid], amount);
}

CMD:balance(playerid)
{
    new buf[32];
    BigInt_ToString(g_BankBalance[playerid], buf, sizeof buf);
    SendClientMessage(playerid, -1, buf);
    return 1;
}
```

All operations return simple success/failure flags (e.g., division by zero yields `false`) so you can guard your logic as needed.

## Contributing

Contributions are welcome! To get started:

- Fork the repository and create a branch for your change.
- Keep commits focused; include tests or Pawn snippets that demonstrate new or fixed behavior when possible.
- Run the CMake build locally to ensure the component/plugin still compiles on your platform.
- Test on both open.mp and SA:MP if possible.
- Open a pull request against `master`, describing the motivation, implementation details, and any testing performed.

If you encounter issues or have feature ideas, feel free to open a GitHub issue with as much detail as possible.
